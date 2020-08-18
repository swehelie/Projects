<?php
/**
 * Created by PhpStorm.
 * User: Duhyun K, Hailey S, Josh W, Sarah W
 * Date: 06/04/2020
 * Time: 12:30PM
 * Source to help get table formatted: https://www.youtube.com/watch?v=bHFoobciCTM;

 * Details: Allows the user to filter based off disaster type
 * (e.g., enter 'Hu', it will pull up natural disasters that contain
 * those words. Not case sensitive).
 */

require_once 'config.inc.php';
require_once 'headerList_NaturalDisaster.inc.php';

?>
<html>
<head>
    <title>NaturalDisasters</title>
    <link rel="stylesheet" href="StyleSheets/base.css">
    <link rel="stylesheet" href="StyleSheets/tableSearchBarFormatting.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
</head>
<body>

<div>
  <table class = table1>
    <h1>Natural Disasters Statistics</h1>

    <?php
    $conn = new mysqli($servername, $username, $password, $database, $port);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $disasterType = $_POST['disasterType'];
        if ($disasterType === null)
            echo "<div><i>Specify a new na</i></div>";
        else if ($disasterType === false)
            echo "<div><i>Specify a name</i></div>";
        else if (trim($disasterType) === "")
            echo "<div><i>Specify a new name</i></div>";
        else {
            /* perform update */
            $sql = "SELECT disasterID, NaturalDisaster.disasterCode, disasterName, startDate
                    FROM NaturalDisaster WHERE UPPER(NaturalDisaster.disasterCode) LIKE CONCAT('%', ?, '%')
                    ORDER BY startDate DESC";
            $stmt = $conn->stmt_init();
            if (!$stmt->prepare($sql)) {
                echo "failed to prepare";
            } else {
                $disasterType = strtoupper($disasterType);
                $stmt->bind_param('s',$disasterType);
                $stmt->execute();
                $conn->commit();
            }
        }
    }
    /* refreshed */
    $sql = "SELECT disasterID, NaturalDisaster.disasterCode, disasterName, totalDeath, totalAffected,
            totalDamageCost, startDate, endDate
            FROM NaturalDisaster WHERE UPPER(NaturalDisaster.disasterCode) LIKE CONCAT('%', ?, '%')
            ORDER BY startDate DESC";
    $stmt = $conn->stmt_init();
    if (!$stmt->prepare($sql)) {
        echo "failed to prepare";
    }
    else {
        $disasterType = strtoupper($disasterType);
        $stmt->bind_param('s',$disasterType);
        $stmt->execute();
        $stmt->bind_result($disasterID,$disasterCode,$disasterName, $totalDeath, $totalAffected, $totalDamageCost,
        $startDate, $endDate);
        ?>
        <form method="POST">
            <input type="hidden" name="searchByDisaster" value="<?= $searchByDisaster ?>">

        <?php

        /* Used to only output the header row only once if a table can be created */
        $count = 1;
        $count1 = 0;
        while ($stmt->fetch()) {

          /* Displays the row header describing the columns only once */
          if ($count === 1) {
              $count1++;
            ?>
            <tr>
                <th>Disaster ID</th>
                <th id="disasterType">Disaster Type</th>
                <th id="nameOfDisaster">Disaster Name</th>
                <th>Total Death</th>
                <th>Total Affected</th>
                <th>Total Damage Cost</th>
                <th>Start Date</th>
                <th>End Date</th>
            </tr>
            <?php
          }

          echo '<tr>';
          echo '<td><a href="show_naturalDisaster.php?id=' . $disasterID . '">' . $disasterID .
          '</td><td>' . $disasterCode. '</td><td>' . $disasterName . '</td><td>' . $totalDeath .
          '</td><td>' . $totalAffected . '</td><td>' . $totalDamageCost .
          '</td><td>' . $startDate . '</td><td>' . $endDate . '</td>';
          echo '</tr>';
          $count++;
        }
    ?><br><br>
          <div class="searchBar">
            <input type="text" class="inputSearch" name="disasterType"
            placeholder="Search by disaster type...">
            <button type="submit"><i class="fa fa-search"></i></button>
          </div>
        </form>
    <?php
    }
    if($count1 === 0)
    {
	?>
	<br><br> Disaster Type Not Found.
	<?php
    }
    $conn->close();

    ?>
</table>
</div>
</body>
</html>
