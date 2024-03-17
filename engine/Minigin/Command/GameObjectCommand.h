#ifndef GAMEOBJECTCOMMAND_H
#define GAMEOBJECTCOMMAND_H

#include "Command.h"
#include "Util/PointerAliases.h"

namespace dae {
	class GameObject;

	class GameObjectCommand : public Command {
	public:
		explicit GameObjectCommand(GameObject *pGameObject)
		    : m_pGameObject{pGameObject} {
		}

		virtual ~GameObjectCommand() = default;

		virtual void Execute() = 0;

	protected:
		[[nodiscard]]
		NonOwningPtrMut<GameObject> GetGameObjectPtr() const {
			return m_pGameObject;
		}

	private:
		NonOwningPtrMut<GameObject> m_pGameObject{};
	};
}// namespace dae

#endif//GAMEOBJECTCOMMAND_H
