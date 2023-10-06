# Creates C resources file from files in given directory
function(create_resources input_dir source_output header_output)
    get_filename_component(HEADER_FILENAME ${header_output} NAME)
    string(REGEX REPLACE "^.*/include/" "" INCLUDE_DIR ${header_output})

    set(NAMESPACE Assets)

    # Create empty output file
    file(WRITE ${source_output} "#include \"${INCLUDE_DIR}\"\n\n")
    file(WRITE ${header_output} "#pragma once\n\n")
    file(APPEND ${header_output} "#include <cstdint>\n")
    file(APPEND ${header_output} "#include <unordered_map>\n")
    file(APPEND ${header_output} "#include <utility>\n")
    file(APPEND ${header_output} "#include <string>\n\n")
    file(APPEND ${header_output} "namespace Assets {\n")

    # Collect input files
    file(GLOB bins ${input_dir}/*)

    # Iterate through input files
    foreach(bin ${bins})
        # Get short filename
        get_filename_component(file-name ${bin} NAME)
        string(REGEX REPLACE "\\.| |-" "_" file_name ${file-name})
        string(REGEX REPLACE "_" "" filename ${file_name})
        string(TOUPPER ${file_name} FILE_NAME)

        # string(REGEX MATCH "([^/]+)$" filename ${bin})

        # Replace filename spaces & extension separator for C compatibility
        string(REGEX REPLACE "\\.| |-" "" filename ${filename})
        message("Embeding ${filename} in C code")

        # Read hex data from file
        file(READ ${bin} filedata HEX)

        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})

        # Append data to output file
        file(APPEND ${source_output} "const uint8_t ${NAMESPACE}::${filename}[] = {${filedata}};\n")
        file(APPEND ${source_output} "static const uint8_t *${filename}Ptr = static_cast<const uint8_t *>(${NAMESPACE}::${filename});\n")
        file(APPEND ${source_output} "const uint32_t ${NAMESPACE}::${filename}Size = sizeof(${NAMESPACE}::${filename});\n")
        file(APPEND ${header_output} "    // Byte array of the ${filename} asset\n")
        file(APPEND ${header_output} "    extern const uint8_t ${filename}[];\n")
        file(APPEND ${header_output} "    // Size of the byte array of the ${filename} asset\n")
        file(APPEND ${header_output} "    extern const uint32_t ${filename}Size;\n")
    endforeach()

    file(APPEND ${header_output} "    // array of assets\n")
    file(APPEND ${header_output} "    extern std::pair<const uint8_t **, const uint32_t> assets[];\n")
    file(APPEND ${header_output} "    // array of assets\n")
    file(APPEND ${header_output} "    enum class AssetsIndex {\n")
    file(APPEND ${source_output} "std::pair<const uint8_t **, const uint32_t> ${NAMESPACE}::assets[] = {\n")

    foreach(bin ${bins})
        get_filename_component(file-name ${bin} NAME)
        string(REGEX REPLACE "\\.| |-" "_" file_name ${file-name})
        string(REGEX REPLACE "_" "" filename ${file_name})
        string(TOUPPER ${file_name} FILE_NAME)
        file(APPEND ${header_output} "        ${FILE_NAME},\n")
        file(APPEND ${source_output} "    { &${filename}Ptr, ${NAMESPACE}::${filename}Size },\n")
    endforeach()

    file(APPEND ${header_output} "    };\n")
    file(APPEND ${header_output} "\n};\n")
    file(APPEND ${source_output} "};\n")

    message("Convertion of ${input_dir} ended successfully")
endfunction()

file(REMOVE ${OUTPUT} ${OUTPUT_HEADER})
create_resources(${INPUT_DIR} ${OUTPUT} ${OUTPUT_HEADER})