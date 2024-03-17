#ifndef COMMAND_H
#define COMMAND_H

namespace dae {
	class Command {
	public:
		virtual ~Command()     = default;
		virtual void Execute() = 0;
	};
}// namespace dae

#endif//COMMAND_H
