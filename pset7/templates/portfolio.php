<div id="portfolio">
    <table class="table table-striped">
        <thead><tr>
            <th>Symbol</th><th>Name</th><th>Shares</th><th>Price</th><th>Total</th>
        </tr></thead>
        <tbody>
        <?php foreach ($positions as $position): ?>
        <tr>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["name"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td>$<?= $position["price"] ?></td>
        <td>$<?= number_format($position["shares"] * $position["price"], 2, '.', ',') ?></td>
        </tr>
        <?php endforeach ?>
        <?php foreach ($cash as $amount): ?>
        <tr>
        <td><strong><?= $amount["total"] ?></strong></td>
        <td><?= $amount["blank"] ?></td>
        <td><?= $amount["blank"] ?></td>
        <td><?= $amount["blank"] ?></td>        
        <td>$<?= $amount["cash"] ?></td>
        </tr>
        <?php endforeach ?>
        </tbody>
    </table>
</div>
<div>
    <strong><a href="logout.php">Log Out</a></strong>
</div>
