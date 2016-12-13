<?php

    //configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // send history array to template
        $id = $_SESSION["id"];
        $rows = query("SELECT * FROM history WHERE id = $id");
        $history = [];
        foreach ($rows as $row)
        {
            $history[] = [
                "id" => $row["id"],
                "transaction" => $row["transaction"],
                "type" => $row["type"],
                "date_time" => $row["date_time"],
                "symbol" => $row["symbol"],
                "shares" => $row["shares"],
                "price" => $row["price"]
            ];
        }
        render("history_form.php", ["history" => $history, "title" => "History"]);
    }
    
?>    
