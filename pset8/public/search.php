<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // search database for places matching $_GET["geo"]
    
    // ensure proper usage
    if (empty($_GET["geo"]))
    {
        http_response_code(400);
        exit;
    }

    $geo = ($_GET["geo"]);

    // just the city entered by name or zip
    $alphanum = (preg_match('/^[a-zA-Z0-9]+$/', $geo));
    if ($alphanum === 1)
    {
        $rows = query("SELECT * FROM places WHERE postal_code LIKE '%$geo%' || place_name LIKE '%$geo%'");
    }
    // multi name city or city state entered
    if ($alphanum === 0)
    {
        $whitespace = (preg_match('/\s/',$geo));

        if ($whitespace === 1)
        {
            $pos = strripos($geo, ' ');
            $len = strlen($geo);
            $pieces = explode(" ", $geo);
            $end = count($pieces);
            $num = count($pieces) - 1;
            $pre = count($pieces) - 2;
            // Two name states
            if ($pieces[$num - 1] === "North" || $pieces[$num - 1] === "north" || $pieces[$num - 1] === "South" || $pieces[$num - 1] === "south" || $pieces[$num - 1] === "New" || $pieces[$num - 1] === "new" || $pieces[$num - 1] === "West" || $pieces[$num - 1] === "west" || $pieces[$num - 1] === "Rhode" || $pieces[$num - 1] === "rhode")
            {
                $sarray = [];
                for ($j = $pre; $j < $end; $j++)
                {
                    $sarray[$j] = $pieces[$j];
                }
                $state = implode(" ", $sarray);
                $carray = [];
                for ($k = 0; $k < $pre; $k++)
                {
                    $carray[$k] = $pieces[$k];
                }
                $city = implode(" ", $carray);
            }
            // Single name or abbreviated states
            else
            {
                $state = $pieces[$num];
                $carray = [];
                for ($i = 0; $i < $num; $i++)
                {
                    $carray[$i] = $pieces[$i];
                }
                $city = implode(" ", $carray);
            }
            // find city and state
            $statelen = strlen($state);
            if ($statelen === 2)
            {
                $rows = query("SELECT * FROM places WHERE place_name LIKE '%$city%' && admin_code1 LIKE '%$state%'");
            }
            if ($statelen > 2)
            {
                $rows = query("SELECT * FROM places WHERE place_name LIKE '%$city%' && admin_name1 LIKE '%$state%'");
            }
        }
    }
    
    // error checking the query
    if ($rows === false)
    {
        print "error";
    }
    foreach ($rows as $row)
    {
        // add place to array
        $places[] = [
            "id" => $row["id"],
            "country_code" => $row["country_code"],
            "postal_code" => $row["postal_code"],
            "place_name" => $row["place_name"],
            "admin_name1" => $row["admin_name1"],
            "admin_code1" => $row["admin_code1"],
            "admin_name2" => $row["admin_name2"],
            "admin_code2" => $row["admin_code2"],
            "admin_name3" => $row["admin_name3"],
            "admin_code3" => $row["admin_code3"],
            "latitude" => $row["latitude"],
            "longitude" => $row["longitude"],
            "accuracy" => $row["accuracy"]
        ];
    }

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
