#pragma once


namespace Musoeun
{
	class MCommand
	{
	public:
		MCommand() {}
		virtual ~MCommand() {}

		virtual void Execute() {	}
	};
}

