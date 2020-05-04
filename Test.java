import java.util.Scanner;
import java.awt.Color;

public class Test {
	public static void main(String[] args) {
		WindowsIO test = new WindowsIO();

		//test.setClipboardText("To je clipboard text");
		System.out.println(test.getClipboardText());
		/*test.keyPress(test.VK_LWIN);
		test.keyPress('R');
		test.keyRelease('R');
		test.keyRelease(test.VK_LWIN);

		try {
			Thread.sleep(500);
		} catch(Exception e) {
			e.printStackTrace();
		}

		test.typeString("mspaint");
		test.keyPress(test.VK_ENTER);
		test.keyRelease(test.VK_ENTER);

		try {
			Thread.sleep(500);
		} catch(Exception e) {
			e.printStackTrace();
		}*/

		//test.mouseMoveAbsoluteVirtual(100, 100);

		/*try {
			Thread.sleep(2000);
		} catch(Exception e) {
			e.printStackTrace();
		}*/

		//test.mouseMoveAbsolute(200, 200);

		/*Scanner sc = new Scanner(System.in);
		System.out.print("Enter text: ");
		String s = sc.nextLine();
		System.out.print("Enter ammount: ");
		int num = sc.nextInt();*/
		/*System.out.println("You have 5s to change focus");

		try {
			Thread.sleep(2000);
		} catch(Exception e) {
			e.printStackTrace();
		}*/
		
		/*System.out.println(test.getMouseX() + " " + test.getMouseY());
		Color c = test.getPixel(test.getMouseX(), test.getMouseY());
		System.out.println(c.getRed() + ", " + c.getGreen() + ", " + c.getBlue());*/

		//test.mousePress(test.VMK_RIGHT);
		//test.mouseRelease(test.VMK_RIGHT);

		/*try {
			Thread.sleep(5000);
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		test.typeString("This program can auto send now"); 
		test.keyPress(test.VK_LCTRL);
		test.keyPress('V');
		test.keyRelease('V');
		test.keyRelease(test.VK_LCTRL);

		test.keyPress(test.VK_ENTER);
		test.keyRelease(test.VK_ENTER);/*

		try {
			Thread.sleep(1000);
		} catch(Exception e) {
			e.printStackTrace();
		}*/

		/*for(int i = 0; i < num; i++) {
			test.typeString(s);
			test.keyPress(test.VK_ENTER);
			test.keyRelease(test.VK_ENTER);
		}*/
	}
}