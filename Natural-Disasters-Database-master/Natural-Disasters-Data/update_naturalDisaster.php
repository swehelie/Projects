<?php
/**
 * Created by PhpStorm.
 * User: Duhyun K, Hailey S, Josh W, Sarah W
 * Date: 06/11/2020
 * Time: 7:43PM
 * Source to help get table formatted: https://www.youtube.com/watch?v=bHFoobciCTM;
 *
 * Details: Checks naturalDisasterID and locationID from URl;
 * users are able to update total deaths on a specific location
 * that was impacted.
 */

 require_once 'config.inc.php';
 require_once 'headerList_NaturalDisaster.inc.php';

// Get disasterID from URL
$id = $_GET['id'];
if ($id === "") {
    header('location: show_naturalDisaster.php');
    exit();
}
if ($id === false) {
    header('location: show_naturalDisaster.php');
    exit();
}
if ($id === null) {
    header('location: show_naturalDisaster.php');
    exit();
}

// Get locationID from URL
$locationID = $_GET['locationID'];
if ($locationID === "") {
    header('location: show_naturalDisaster.php');
    exit();
}
if ($locationID === false) {
    header('location: show_naturalDisaster.php');
    exit();
}
if ($locationID === null) {
    header('location: show_naturalDisaster.php');
    exit();
}

?>
<html>
<head>
    <title>NautralDisasters</title>
    <link rel="stylesheet" href="StyleSheets/base.css">
    <link rel="stylesheet" href="StyleSheets/tableSearchBarFormatting.css">
</head>
<body>
<div>
  <table class="table1">
    <h1>Update Natural Disaster</h1>
    <?php

    // Create connection
    $conn = new mysqli($servername, $username, $password, $database, $port);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }



    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $totalDeath = $_POST['totalDeath'];
        if ($totalDeath === null)
            echo "<div><i>Enter a numeric value for total death</i></div>";
        else if ($totalDeath === false)
            echo "<div><i>Enter a numeric value for total death</i></div>";
        else if (trim($totalDeath) === "")
            echo "<div><i>Enter a numeric value for total death</i></div>";
        else {
            /* Retrieve current total death for location */
            $sql = "SELECT Impact.totalDeath FROM Impact WHERE Impact.disasterID = ? AND Impact.locationID = ?";
            $stmt = $conn->stmt_init();
            if (!$stmt->prepare($sql)) {
                echo "failed to prepare";
            } else {
                $stmt->bind_param('si', $id, $locationID);
                $stmt->bind_result($currentTotalDeath);
                $stmt->execute();

                /* Store in a variable */
                while($stmt->fetch()) {
                  $currentTotalDeath;
                }

                /* Update total death from user input */
                $sql = "UPDATE Impact SET totalDeath = ? WHERE Impact.disasterID = ? AND Impact.locationID = ?";
                $stmt = $conn->stmt_init();
                if (!$stmt->prepare($sql)) {
                    echo "failed to prepare";
                } else {
                    $stmt->bind_param('isi', $totalDeath,$id, $locationID);
                    $stmt->execute();
                    $conn->commit();


                    /* Retrieve new total death for location */
                    $sql = "SELECT Impact.totalDeath FROM Impact WHERE Impact.disasterID = ? AND Impact.locationID = ?";
                    if (!$stmt->prepare($sql)) {
                        echo "failed to prepare";
                    } else {
                        $stmt->bind_param('si', $id, $locationID);
                        $stmt->bind_result($totalDeath);
                        $stmt->execute();
                    }

                    /* Subtract the difference, so it then can be added to total death for the natural disaster,
                    as there are two separate death counts - one overall and one by impact location */
                    $differenceInDeath = $totalDeath - $currentTotalDeath;

                    /* Retrieve overall total death from natural disaster*/
                    $sql = "SELECT NaturalDisaster.totalDeath FROM NaturalDisaster WHERE NaturalDisaster.disasterID = ?";
                    if (!$stmt->prepare($sql)) {
                        echo "failed to prepare";
                    } else {
                        $stmt->bind_param('s', $id);
                        $stmt->bind_result($overallTotalDeath);
                        $stmt->execute();
                    }

                    while($stmt->fetch()) {
                      $overallTotalDeath;
                    }

                    /* Update overall total death from natural disaster */
                    $sql = "UPDATE NaturalDisaster SET totalDeath = ? WHERE NaturalDisaster.disasterID = ?";
                    $stmt = $conn->stmt_init();
                    if (!$stmt->prepare($sql)) {
                        echo "failed to prepare";
                    } else {
                            /* Adds the difference to overall total death from natural disaster,
                            then gets updated to the table */
                            $newTotalDeath = $differenceInDeath + $overallTotalDeath;
                            $stmt->bind_param('is', $newTotalDeath,$id);
                            $stmt->execute();
                            $conn->commit();
                          }
                        }
              }
            }
        }


    /* Refresh the Data */
    $sql = "SELECT NaturalDisaster.disasterID, NaturalDisaster.disasterName, Impact.totalDeath,
    Impact.totalAffected, Impact.totalDamageCost, startDate, endDate, Location.isoCode,
    Location.stateCode, Location.cityName, Location.locationID, COUNT(*) AS 'ReportsFiled'
    FROM DisasterClaim
    INNER JOIN NaturalDisaster ON NaturalDisaster.disasterID = DisasterClaim.disasterID
    INNER JOIN Impact ON NaturalDisaster.disasterID = Impact.disasterID
    INNER JOIN Location ON Impact.locationID = Location.locationID
    WHERE (DisasterClaim.locationID = Location.locationID) AND (NaturalDisaster.disasterID = ?) AND (Location.locationID = ?)
    GROUP BY Impact.locationID";
    $stmt = $conn->stmt_init();
    if (!$stmt->prepare($sql)) {
        echo "failed to prepare";
    }
    else {
        $stmt->bind_param('si',$id, $locationID);
        $stmt->execute();
        $stmt->bind_result($disasterID, $disasterName, $totalDeath,
        $totalAffected, $totalDamageCost, $startDate, $endDate, $isoCode,
        $stateCode, $cityName, $locationID, $reportsFiled);
        ?>
        <form method="POST">
            <input type="hidden" name="updateTotalDeath" value="<?= $updateTotalDeath ?>">
        <?php
        echo "<div>";

        /* Used to only output the header row only once if a table can be created */
        $count = 1;
        while ($stmt->fetch()) {

          /* Displays the row header describing the columns only once */
          if ($count === 1) {
            ?>
            <tr>
                <th id="nameOfDisaster">Disaster Name</th>
                <th>Total Death by Area</th>
                <th>Total Affected by Area</th>
                <th>Total Damage Cost by Area</th>
                <th>Start Date</th>
                <th>End Date</th>
                <th>Country</th>
                <th>State</th>
                <th>City Name</th>
                <th>Reports Filed by Area</th>
            </tr>
            <?php
          }

          echo '<tr>';
          echo
          '</td><td>' . '<a href="show_naturalDisaster.php?id=' . $disasterID . '">' . $disasterName . '</td><td>' . $totalDeath .
          '</td><td>' . $totalAffected. '</td><td>' . $totalDamageCost .
          '</td><td>' . $startDate . '</td><td>' . $endDate . '</td><td>' . $isoCode .
          '</td><td>' . $stateCode . '</td><td>' . $cityName . '</td><td>' . $reportsFiled . '</td>';
          echo '</tr>';
          $count++;
        }
        echo "</div>";
    ?><br><br>
        <div class="searchBar">
          <input type="text" class="updateSearch" name="totalDeath"
          placeholder="Update the total death...">
          <button type="submit" id="enterButton">Enter</button>
        </div>
      </form>
    <?php
    }

    $conn->close();

    ?>
</table>
</div>
</body>
</html>
