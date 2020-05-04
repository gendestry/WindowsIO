import java.util.Scanner;

public class Test {
	public static void main(String[] args) {
		WindowsIO io = new WindowsIO();

		Scanner sc = new Scanner(System.in);
		System.out.print("Enter text: ");
		String s = sc.nextLine();
		System.out.print("Enter ammount: ");
		int num = sc.nextInt();
		
		System.out.println("You have 5s to change focus");

		try {
			Thread.sleep(5000);
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		for(int i = 0; i < num; i++) {
			test.typeString(s);
			test.keyPress(test.VK_ENTER);
			test.keyRelease(test.VK_ENTER);
		}
	}
}