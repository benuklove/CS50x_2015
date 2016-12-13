<?php

    // configuration
    require("../includes/config.php");
    
    $id = $_SESSION["id"];
    $rows = query("SELECT * FROM portfolios WHERE id = $id");
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => number_format($stock["price"], 2, '.', ','),
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
  
    $cash_balance = query("SELECT cash FROM users WHERE id = $id");
    $cb = $cash_balance[0]["cash"];
    $cash[] = [
        "total" => "Cash Available",
        "blank" => "",
        "cash" => number_format($cb, 2, '.', ',') ];
    //dump($cash_balance);    
    render("portfolio.php", ["positions" => $positions, "cash" => $cash, "title" => "Portfolio"]);
?>
