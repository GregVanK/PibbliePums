/*
*@author: Greg VanKampen 
*@file: SoundPlayer.cpp
*@description: A class which plays sound
*/
#include "SoundPlayer.h"
#include <cassert>
namespace {
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ * ListenerZ);
}
GEX::SoundPlayer::SoundPlayer() 
	: _soundsBuffers()
	, _sounds()
{
	_volume = 50;
	loadBuffer(SoundEffectID::CursorMove, "Media/Sound/nav.wav");
	loadBuffer(SoundEffectID::Select, "Media/Sound/select.wav");
	loadBuffer(SoundEffectID::Back, "Media/Sound/back.wav");

	// Listener points towards the screen (default in SFML)
	sf::Listener::setDirection(192.f, 192.f, 0.f);
}

void GEX::SoundPlayer::play(SoundEffectID effect)
{
	play(effect, getListenerPosition());

}

void GEX::SoundPlayer::play(SoundEffectID effect, sf::Vector2f position)
{
	_sounds.push_back(sf::Sound());
	sf::Sound& sound = _sounds.back();

	sound.setBuffer(*_soundsBuffers[effect]);
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);
	sound.setVolume(_volume);
	sound.play();
}

void GEX::SoundPlayer::removeStoppedSounds()
{
	_sounds.remove_if([](const sf::Sound& s) {
		return s.getStatus() == sf::Sound::Stopped;
	});
}

void GEX::SoundPlayer::setListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f GEX::SoundPlayer::getListenerPosition() const
{
	sf::Vector3f pos = sf::Listener::getPosition();
	return sf::Vector2f(pos.x, -pos.y);
}

void GEX::SoundPlayer::loadBuffer(SoundEffectID id, const std::string path)
{
	std::unique_ptr<sf::SoundBuffer> buffer(new sf::SoundBuffer);
	if (!buffer->loadFromFile(path))
		throw std::runtime_error("Sound file failed to load");
	auto inserted = _soundsBuffers.insert(std::make_pair(id, std::move(buffer)));
	assert(inserted.second);
}
