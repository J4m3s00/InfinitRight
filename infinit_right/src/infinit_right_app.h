#pragma once

namespace IR {

	class InfinitRightApp
	{
	public:
		InfinitRightApp();
		~InfinitRightApp();
	private:
		InfinitRightDrawing*			fActiveDrawing;
		IRVector<InfinitRightDrawing*>	fLoadedDrawings;

		InfinitRightUndoManager			fUndoManager;
	public:
		void							Initialize();

		void							SetActiveDrawing(InfinitRightDrawing* drawing);
		InfinitRightDrawing*			GetActiveDrawing();


		InfinitRightUndoManager&		GetUndoManager();
	public:
		static InfinitRightApp& gApp()
		{
			static InfinitRightApp    instance;
			return instance;
		}
	};

}