#ifndef CONTROLLERCOMMANDS_H
#define CONTROLLERCOMMANDS_H

#include "Components/PlayableCharacter.h"
#include "GameObject.h"
#include "GameObjectCommand.h"
#include "GameTime.h"

namespace dae {
	enum class Movement { Positive, Neutral, Negative };

	template<Movement X, Movement Y>
	class ControllerCommand final : public GameObjectCommand {
	public:
		ControllerCommand(
		        NonOwningPtrMut<GameObject> pGameObject, NonOwningPtrMut<PlayableCharacter> pPlayableCharacter
		)
		    : GameObjectCommand(pGameObject)
		    , m_pPlayableCharacter{pPlayableCharacter} {
		}

	private:
		[[nodiscard]]
		float GetXFactor() const {
			switch (X) {
				case Movement::Positive:
					return 1.f;
				case Movement::Neutral:
					return 0.f;
				case Movement::Negative:
					return -1.f;
			}

			return 0.f;
		}

		[[nodiscard]]
		float GetYFactor() const {
			switch (Y) {
				case Movement::Positive:
					return 1.f;
				case Movement::Neutral:
					return 0.f;
				case Movement::Negative:
					return -1.f;
			}

			return 0.f;
		}

		void Execute() override {
			m_pPlayableCharacter->Move(GetXFactor(), GetYFactor());
		}

		NonOwningPtrMut<PlayableCharacter> m_pPlayableCharacter{};
	};
}// namespace dae

#endif//CONTROLLERCOMMANDS_H
