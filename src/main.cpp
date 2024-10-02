// LMAO WTF HAHAHAAHHAHAHHHA LOLOLLOOLOOLOLOLOLOLLOLOLOL TROLOLOOOOOOOOOOOOOAH

#include "Geode/cocos/actions/CCActionInstant.h"
#include "Geode/cocos/actions/CCActionInterval.h"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/loader/Mod.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <cstdint>
#include <random>

class $modify(MyPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) override {
		PlayLayer::destroyPlayer(player, object);

		if (geode::Mod::get()->getSettingValue<bool>("random-respawn") == true) {
			int minRandom = geode::Mod::get()->getSettingValue<int64_t>("random-min");
			int maxRandom = geode::Mod::get()->getSettingValue<int64_t>("random-max");

			if (minRandom <= maxRandom) {
				std::mt19937 generator(std::random_device{}());
				std::uniform_real_distribution<float> distribution(static_cast<float>(minRandom), static_cast<float>(maxRandom));

				float randomTime = distribution(generator);

				if (auto* respawnSequence = this->getActionByTag(0x10)) {
					this->stopAction(respawnSequence);
					auto* newSequence = cocos2d::CCSequence::create(
						cocos2d::CCDelayTime::create(randomTime),
						cocos2d::CCCallFunc::create(this, callfunc_selector(PlayLayer::delayedResetLevel)),
						nullptr
					);
					newSequence->setTag(0x10);
					this->runAction(newSequence);
				}
			}
		}
	}
};
