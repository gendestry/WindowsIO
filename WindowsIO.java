import java.awt.Color;
import java.awt.Rectangle;

public class WindowsIO {

	// (vkcode) KEY CODES (more at: https://docs.microsoft.com/sl-si/windows/win32/inputdev/virtual-key-codes)
	public static final char VK_ENTER	  = (char) 0x0D;
	public static final char VK_ALT      = (char) 0x12;
	public static final char VK_CAPSLOCK = (char) 0x14;
	public static final char VK_PRINTSCR = (char) 0x2C;
	public static final char VK_LSHIFT   = (char) 0xA0;
	public static final char VK_LCTRL    = (char) 0xA2;
	public static final char VK_LWIN     = (char) 0x5B;
	public static final char VK_SLEEP    = (char) 0x5F;
	public static final char VK_NUMLOCK  = (char) 0x90;

	// (vmcode) MOUSE KEY CODES
	public static final char VMK_LEFT    = (char) 0x02;
	public static final char VMK_RIGHT   = (char) 0x08;
	public static final char VMK_MIDDLE  = (char) 0x20;

	// get screen sizes
	public native int getScreenSizeX();
	public native int getScreenSizeY();
	public native int getVirtualScreenSizeX();
	public native int getVirtualScreenSizeY();

	// gets the foreground window's position and size
	public native Rectangle getForegroundWindowMetrics();

	// press/release a specific key (not unicode friendly)
	public native void keyPress(char vkcode);
	public native void keyRelease(char vkcode);

	// type (press & release) a unicode char/string
	public native void typeChar(char c);
	public native void typeString(String str);

	// press/release mouse key
	public native void mousePress(char vmcode);
	public native void mouseRelease(char vmcode);

	// scroll wheel movement
	public native void mouseScroll(int ammount);

	// get mouse position
	public native int getMouseX();
	public native int getMouseY();

	// mouse movement
	public native void mouseMove(int x, int y);				// relative to the main monitor
	public native void mouseMoveVirtual(int x, int y);		// relative to virtual screen space (multiple monitors)
	public native void mouseMoveRelative(int x, int y);		// relative to current position

	// get pixel color at position
	public native Color getPixel(int x, int y);
	public native byte[] getScreenshot(int x, int y, int width, int height);	// returns a BGR array of size (width * height * 3)

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