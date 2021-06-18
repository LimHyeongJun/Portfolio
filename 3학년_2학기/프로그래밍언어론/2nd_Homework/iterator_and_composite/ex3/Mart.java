package iterator_and_composite.ex3;

import java.util.*;

public class Mart {
	public static void main(String[] args) {
		Beverage beverage = new Beverage();
		Ramen ramen = new Ramen();
		Snack snack = new Snack();
		
		MartStaff martStaff = new MartStaff(beverage, ramen, snack);
		
		martStaff.printProduct();
		martStaff.printOnSale();
		
		System.out.println("\nCustomer asks, is the 포카리스웨트 on sale?");
		System.out.print("Mart Staff says: ");
		if(martStaff.isOnSale("포카리스웨트")) {
			System.out.println("Yes");
		} else {
			System.out.println("No");
		}
		
		System.out.println("\nCustomer asks, is the 양파링 on sale?");
		System.out.print("Mart Staff says: ");
		if(martStaff.isOnSale("양파링")) {
			System.out.println("Yes");
		} else {
			System.out.println("No");
		}
	}
}
