package iterator_and_composite.ex3;

import java.util.Iterator;

public class MartStaff {
	Product beverage;
	Product ramen;
	Product snack;
	
	public MartStaff(Product beverage, Product ramen, Product snack) {
		this.beverage = beverage;
		this.ramen = ramen;
		this.snack = snack;
	}
	
	public void printProduct() {
		Iterator beverageIterator = beverage.createIterator();
		Iterator ramenIterator = ramen.createIterator();
		Iterator snackIterator = snack.createIterator();
		
		System.out.println("PRODUCT\n----\nBEVERAGE");
		printProduct(beverageIterator);
		System.out.println("\nRAMEN");
		printProduct(ramenIterator);
		System.out.println("\nSNACK");
		printProduct(snackIterator);
	}
	
	private void printProduct(Iterator iterator) {
		while(iterator.hasNext()) {
			ProductItem productItem = (ProductItem)iterator.next();
			System.out.print(productItem.getName() + ", ");
			System.out.print(productItem.getPrice() + " -- ");
			System.out.println(productItem.getDescription());
		}
	}
	
	public void printOnSale() {
		System.out.println("\nON SALE PRODUCT\n-------------");
		printOnSale(beverage.createIterator());
		printOnSale(ramen.createIterator());
		printOnSale(snack.createIterator());
	}
	
	private void printOnSale(Iterator iterator) {
		while(iterator.hasNext()) {
			ProductItem productItem = (ProductItem)iterator.next();
			if(productItem.isOnSale()) {
				System.out.print(productItem.getName() + ", ");
				System.out.print(productItem.getPrice() + " -- ");
				System.out.println(productItem.getDescription());
			}
		}
	}
	
	public boolean isOnSale(String name) {
		Iterator beverageIterator = beverage.createIterator();
		if(isOnSale(name, beverageIterator)) {
			return true;
		}
		Iterator ramenIterator = ramen.createIterator();
		if(isOnSale(name, ramenIterator)) {
			return true;
		}
		Iterator snackIterator = snack.createIterator();
		if(isOnSale(name, snackIterator)) {
			return true;
		}
		return false;
	}
	
	private boolean isOnSale(String name, Iterator iterator) {
		while(iterator.hasNext()) {
			ProductItem productItem = (ProductItem)iterator.next();
			if(productItem.getName().equals(name)) {
				if(productItem.isOnSale()) {
					return true;
				}
			}
		}
		return false;
	}
}
