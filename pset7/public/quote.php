<?php

    //configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        if (empty($_POST["symbol"]))
        {
            apologize("You must enter a stock symbol.");
        }
        else
        {
            $quote = lookup($_POST["symbol"]);
            $quote_array[] = [
                "name" => $quote["name"],
                "symbol" => strtoupper($quote["symbol"]),
                "price" => number_format($quote["price"], 2, '.', ',')
            ];
            
        }
        //dump($quote_array);
        // send quote array to template
        render("quote_result_form.php", ["quote_array" => $quote_array, "title" => "Quote"]);
    }
    
?>    
