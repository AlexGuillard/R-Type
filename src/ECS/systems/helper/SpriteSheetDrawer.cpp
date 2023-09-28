/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** SpriteSheetDrawer
*/

#include <utility>

#include <raylib.h>

#include "ECS/Systems/Helper/SpriteSheetDrawer.hpp"

namespace ECS::Systems::Helper {

	SpriteSheetDrawer::SpriteSheetDrawer(Texture2D texture, Vector2 frameRatio,
		Vector2 start, Vector2 end, bool boomerang, std::size_t frame, bool forward)
		: m_texture(texture), m_rows(frameRatio.y), m_columns(frameRatio.x),
		m_boomerang(boomerang), m_currentFrame(frame), m_forward(forward)
	{
		this->m_frameSize = {
			(float)texture.width / m_columns,
			(float)texture.height / m_rows
		};
		this->setRange(start, end);
	}

	void SpriteSheetDrawer::setRange(Vector2 start, Vector2 end)
	{
		this->m_start = start.x + start.y * m_columns;
		this->m_end = end.x + end.y * m_columns;
		if (this->m_start > this->m_end) {
			std::swap(this->m_start, this->m_end);
		}
		this->m_nbFrames = this->m_end - this->m_start;
	}

	void SpriteSheetDrawer::draw(int row, int column, int posX, int posY)
	{
		Rectangle source = {
			(float)column * m_frameSize.x,
			(float)row * m_frameSize.y,
			m_frameSize.x,
			m_frameSize.y
		};
		Rectangle dest = {
			(float)posX,
			(float)posY,
			m_frameSize.x,
			m_frameSize.y
		};
		DrawTexturePro(m_texture, source, dest, { 0, 0 }, 0, WHITE);
	}

	void SpriteSheetDrawer::draw(const Vector2 &position)
	{
		int realFrame = m_currentFrame + m_start;
		int row = realFrame / m_columns;
		int column = realFrame % m_columns;

		this->draw(row, column, position.x, position.y);
	}

	int SpriteSheetDrawer::next()
	{
		if (m_nbFrames == 0) {
			return m_currentFrame;
		}
		if (m_forward) {
			m_currentFrame = (m_currentFrame + 1) % m_nbFrames;
		} else {
			m_currentFrame = (m_currentFrame - 1) % m_nbFrames;
		}
		if (m_boomerang && (m_currentFrame == 0 || m_currentFrame == (m_nbFrames - 1))) {
			m_forward = !m_forward;
		}
		return m_currentFrame;
	}

	bool SpriteSheetDrawer::isForward() const
	{
		return m_forward;
	}

	int SpriteSheetDrawer::drawNext(const Vector2 &position)
	{
		next();
		draw(position);
		return m_currentFrame;
	}

	void SpriteSheetDrawer::reset()
	{
		m_currentFrame = m_start;
	}

}; // namespace ECS::Systems::Helper
