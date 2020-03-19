#pragma once

namespace IR {

	class IRUUID
	{
	public:
		IRUUID();
		// the bits are reversed
		//	for example:
		//	{09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
		//	'975DE909' 'd5434C36' '4CFFDF8A' 'A741ECE0'
		IRUUID(u32  a, u32  b, u32  c, u32  d);
		// copy the bytes one by one
		IRUUID(const IRUUID& src);
		~IRUUID();

		IRUUID& operator=(const IRUUID& src);
		bool		operator==(const IRUUID& id) const;
		bool		operator!=(const IRUUID& id) const;
		bool    	operator < (const IRUUID& iid) const;

		IRString			ToString() const;
		bool			FromString(const IRString& id);


		// create four 32 Bit integer from the components of the GUID structure
		// the bits are reversed
		//	for example:
		//	{09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
		//	'975DE909' 'd5434C36' '4CFFDF8A' 'A741ECE0'
		void			GetIRUUID(u32& out1, u32& out2, u32& out3, u32& out4) const;
		const IRUUID& CreateNew();
		bool 			IsValid() const;
		const u8* GetData() const;
		u8* GetData();
	protected:
		// {09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
		u8		fData[16];
	};

}