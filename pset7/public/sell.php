<?php

    //configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $id = $_SESSION["id"];
        $rows = query("SELECT * FROM portfolios WHERE id = $id");
        $positions = [];
        foreach ($rows as $row)
        {
            $positions[] = [
                "symbol" => $row["symbol"],
                // "shares" =>
            ];    
        }
        render("sell_form.php", ["positions" => $positions, "title" => "Sell"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (preg_match("/^\d+$/", $_POST["shares"]) === false)
        {
            apologize("You can only sell positive, whole number shares, silly.");
        }
        else
        {
            $id = $_SESSION["id"];
            $stock_array = query("SELECT * FROM portfolios WHERE symbol = ? AND id = $id", $_POST["symbol"]);
            $shares_avail = $stock_array[0]["shares"];
            
            if ($_POST["shares"] > $shares_avail)
            {
                apologize("You do not have that many shares.");
            }
            else
            {
                // If shares is all shares, delete row; else update shares from portfolios
                if ($_POST["shares"] === $shares_avail)
                {
                    $result0 = query("DELETE FROM portfolios WHERE symbol = ? AND id = $id", $_POST["symbol"]);
                }
                if ($_POST["shares"] < $shares_avail)
                {
                    $result1 = query("UPDATE portfolios SET shares = shares - ? WHERE id = $id AND symbol = ?", $_POST["shares"], $_POST["symbol"]);
                }
                
                // find total amount for proceeds
                $inquire = lookup($_POST["symbol"]);
                $proceeds = $_POST["shares"] * $inquire["price"];
                
                // update cash total in users
                $result2 = query("UPDATE users SET cash = cash + $proceeds WHERE id = $id");
                
                // update history table
                $today = date("F j, Y, g:i a");
                $type = "SELL";
                $result3 = query("INSERT INTO history (id, type, date_time, symbol, shares, price) VALUES($id, ?, ?, ?, ?, ?)", $type, $today, $_POST["symbol"], $_POST["shares"], $inquire["price"]);
                if ($result3 === false)
                {
                    apologize("Error communicating with database.");
                }
                if ($result2 !== false && $result0 !== false || $result1 !== false)
                {
                    redirect("index.php");
                }
            }
        }
    }

    
?>    
