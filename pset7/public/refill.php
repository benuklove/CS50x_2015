<?php

    //configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("refill_form.php", ["title" => "Refill"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        if (empty($_POST["amount"]))
        {
            apologize("You must enter an amount.");
        }
        else
        {
            $id = $_SESSION["id"];
            $refill = $_POST["amount"];
            $result = query("UPDATE users SET cash = cash + $refill WHERE id = $id");
            if ($result !== false)
            {
                redirect("index.php");
            }
            else
            {
                apologize("Error communicating with database.");
            }
        }
    }
    
?>    
