#include "VirtualKeyboardLinux.h"

int main()
{
	cout<<"\nVirtual Keyboard session start...\n";
	
	// Create a smart unique ptr to VirtualKeyboard base class
	unique_ptr<virtualKeyboard> pVk (new virtualKeyboardLinux);

	// To register ^q as exit command for this application
	pVk->setUp();

	// Run the thread in loop
	while(1)
	{
		pVk->execute();
	}

	return 0;
}