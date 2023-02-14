package com.example.TaskC_hy452;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import io.swagger.v3.oas.annotations.*;
import io.swagger.v3.oas.annotations.OpenAPIDefinition;
import io.swagger.v3.oas.annotations.info.Info;

@SpringBootApplication
@RestController
@OpenAPIDefinition(info = @Info(title="Currency Conversion API", description="Given an amount and a currency, get back the amount in any other supported currency" ))
public class TaskCHy452Application {

	public static void main(String[] args) {
		SpringApplication.run(TaskCHy452Application.class, args);
	}
	
	@Operation(summary = "Return the given amount in the desired currency")
	@GetMapping("/CurrencyExchange")
	public double hello(@RequestParam(value= "from", defaultValue= "EUR")String from, @RequestParam(value= "to", defaultValue="USD") String to, @RequestParam(value= "amount", defaultValue="0") double amount) {
		if(amount==0) {return 0;}
		double amountinEUR	= 0; 
		double outputamount	= 0;

		switch (from) {
		case "EUR":
			amountinEUR=amount;
			break;
		case "USD":
			amountinEUR=amount * 0.97;
			break;
		case "GBP":
			amountinEUR=amount * 1.15;
			break;
		case "HRK":
			amountinEUR=amount * 0.13;
			break;
		case "CNY":
			amountinEUR=amount * 0.14;
			break;
		default:
            return -1;
		}
		
		switch (to) {
		case "EUR":
			outputamount=amountinEUR;
			break;
		case "USD":
			outputamount=amountinEUR / 0.97;
			break;
		case "GBP":
			outputamount=amountinEUR / 1.15;
			break;
		case "HRK":
			outputamount=amountinEUR / 0.13;
			break;
		case "CNY":
			outputamount=amountinEUR / 0.14;
			break;
		default:
			return -1;
		}
		
		return outputamount;
	}

}
