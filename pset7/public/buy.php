<?php

    //configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        if (empty($_POST["symbol"]) || empty($_POST["shares"]))
        {
            apologize("You must provide a stock and the number of shares, silly.");
        }
        if (preg_match("/^\d+$/", $_POST["shares"]) === false)
        {
            apologize("You can only purchase positive, whole number shares, silly.");
        }
        
        $id = $_SESSION["id"];
        $cash_array = query("SELECT * FROM users WHERE id = $id");
        $avail_cash = $cash_array[0]["cash"];
        $inquire = lookup($_POST["symbol"]);
        $pershare = $inquire["price"];
        $numshares = $_POST["shares"];
        $ticker = strtoupper($_POST["symbol"]);
        $cost = ($numshares * $pershare);

        if ($avail_cash >= $cost)
        {
            $result0 = query("INSERT INTO portfolios (id, symbol, shares) VALUES($id, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $ticker, $_POST["shares"]);
            // Update user's cash balance
            $result1 = query("UPDATE users SET cash = cash - $cost WHERE id = $id");
            // update history table
            $today = date("F j, Y, g:i a");
            $type = "BUY";
            $result2 = query("INSERT INTO history (id, type, date_time, symbol, shares, price) VALUES($id, ?, ?, ?, ?, ?)", $type, $today, $ticker, $numshares, $pershare);
            if ($result2 === false)
            {
                //dump($today);
                apologize("Error communicating with database.");
            }
        }
        else
        {
            apologize("Uh oh, you don't have enough money for that.");
        }
        
        if ($result0 !== false && $result1 !== false)
        {
            redirect("index.php");
        }
        else
        {
            apologize("Error communicating with database.");
        }
    }
    
?>    
