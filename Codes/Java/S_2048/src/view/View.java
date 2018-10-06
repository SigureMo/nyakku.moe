package view;

import java.util.Scanner;
import model.Model;

public class View {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		System.out.println("欢迎玩这个特无聊的S_2048");
		System.out.println("游戏开始");
		Model model = new Model();
		model.newgame();
		System.out.println(model.toString());
		String s = "";
		while(s != "exit") {
			System.out.println("请输入方向");
			s = in.nextLine();
			model.move(s);
			model.increase();
			System.out.println(model.toString());
		}
		in.close();
		

	}

}
