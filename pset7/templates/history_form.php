<form action="history.php" method="get">

<div id="portfolio">

    <table class="table table-striped">
        <thead><tr>
            <th>Transaction</th><th>Date/Time (UTC)</th><th>Symbol</th><th>Shares</th><th>Price</th>
        </tr></thead>
        <tbody>
        <?php foreach ($history as $h): ?>
        <tr>
        <td><?= $h["type"] ?></td>
        <td><?= $h["date_time"] ?></td>
        <td><?= $h["symbol"] ?></td>
        <td><?= $h["shares"] ?></td>
        <td>$<?= number_format($h["price"], 2, '.', ',') ?></td>
        </tr>
        <?php endforeach ?>
        </tbody>
    </table>
</div>
<div>
    <strong><a href="logout.php">Log Out</a></strong><br>
</div>
<div>
    or go back to <a href="index.php">portfolio</a>
</div>
</form>
