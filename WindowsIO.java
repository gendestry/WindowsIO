import java.awt.Color;

public class WindowsIO {

	// (vkcode) KEY CODES (more at: https://docs.microsoft.com/sl-si/windows/win32/inputdev/virtual-key-codes)
	public final char VK_ENTER	  = (char) 0x0D;
	public final char VK_ALT      = (char) 0x12;
	public final char VK_CAPSLOCK = (char) 0x14;
	public final char VK_PRINTSCR = (char) 0x2C;
	public final char VK_LSHIFT   = (char) 0xA0;
	public final char VK_LCTRL    = (char) 0xA2;
	public final char VK_LWIN     = (char) 0x5B;
	public final char VK_SLEEP    = (char) 0x5F;
	public final char VK_NUMLOCK  = (char) 0x90;

	// (vmcode) MOUSE KEY CODES
	public final char VMK_LEFT    = (char) 0x02;
	public final char VMK_RIGHT   = (char) 0x08;
	public final char VMK_MIDDLE  = (char) 0x20;


	// press / release a specific key (not unicode friendly)
	public native void keyPress(char vkcode);
	public native void keyRelease(char vkcode);

	// type (press & release) a unicode char/string
	public native void typeChar(char c);
	public native void typeString(String str);

	// press / release mouse key
	public native void mousePress(char vmcode);
	public native void mouseRelease(char vmcode);

	// scroll wheel movement
	public native void mouseScroll(int ammount);

	// get mouse position
	public native int getMouseX();
	public native int getMouseY();

	// mouse movement
	public native void mouseMoveRelative(int x, int y);				// relative to current position
	public native void mouseMoveAbsolute(int x, int y);				// relative to the main monitor
	public native void mouseMoveAbsoluteVirtual(int x, int y);		// relative to virtual screen space (multiple monitors)

	// get pixel color at position
	public native Color getPixel(int x, int y);

	// clipboard manipulation
	public native String getClipboardText();
	public native void setClipboardText(String text);


	// load the dll
	static {
		try {
			System.loadLibrary("WindowsIO");
		} catch (Exception e) {
			System.out.println("DLL not found!");
		}
	}
}