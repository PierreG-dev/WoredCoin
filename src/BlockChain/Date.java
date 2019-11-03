package BlockChain;

import java.util.Calendar;

public class Date {

	private static Calendar dateCourante = Calendar.getInstance();
	private static int day = dateCourante.get(Calendar.DAY_OF_MONTH);
	private static int month = dateCourante.get(Calendar.MONTH);
	private static int year = dateCourante.get(Calendar.YEAR);
	private static int hour = dateCourante.get(Calendar.HOUR_OF_DAY);
	private static int minute = dateCourante.get(Calendar.MINUTE);
	private static int second = dateCourante.get(Calendar.SECOND);
	
	public static String chaine() {
		String day = String.valueOf(Date.day);
		String month = String.valueOf(Date.month);
		String year = String.valueOf(Date.year);
		String hour = String.valueOf(Date.hour);
		String minute = String.valueOf(Date.minute);
		String second = String.valueOf(Date.second);
		
		
		if (Date.day < 10)
			day = '0' + day;
		if (Date.month < 10)
			month = '0' + month;
		if (Date.year < 10)
			year = '0' + year;
		if (Date.hour < 10)
			hour = '0' + hour;
		if (Date.minute < 10)
			minute = '0' + minute;
		if (Date.second < 10)
			second = '0' + second;
		
		return "[ " + day + '/' + month + '/' + year + "  " + hour + ':' + minute + ':' + second + " ]";
	}
	
	public static void print() {
		System.out.println(Date.chaine());
	}
	
}
