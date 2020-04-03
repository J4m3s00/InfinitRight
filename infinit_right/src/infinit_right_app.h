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

		IRMap<IRString, TBridgeFn>		fBridgeFns;
		IRMap<IRString, TObjectConstFn>	fObjectTypes;
	public:
		void							Initialize();

		void							SetActiveDrawing(InfinitRightDrawing* drawing);
		InfinitRightDrawing*			GetActiveDrawing();


		InfinitRightUndoManager&		GetUndoManager();

		void RegisterBridgeFunction(const IRString& name, const TBridgeFn& fn);
		IRJson CallBridgeFunction(const IRString& name, const IRJson& input);

		void RegisterObject(const IRString& name, const TObjectConstFn& fn);

		static InfinitRightObject* new_object(const IRString& type, const IRUUID& uuid = IRUUID().CreateNew());
		//GETTER FOR THE INIT FN
	public:

		static InfinitRightApp& gApp()
		{
			static InfinitRightApp    instance;
			return instance;
		}
	};

}