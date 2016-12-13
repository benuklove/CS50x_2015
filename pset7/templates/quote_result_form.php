<form action="quote.php" method="post">
    <fieldset>
        <div>
        <?php foreach ($quote_array as $quotes): ?>
        A share of <?= $quotes["name"] ?> (<?= $quotes["symbol"] ?>) will run ya 'bout $<?= $quotes["price"] ?>.
        <?php endforeach ?>
        </div>
    </fieldset>
</form> 
