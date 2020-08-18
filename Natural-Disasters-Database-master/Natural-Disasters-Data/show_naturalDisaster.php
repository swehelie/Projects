<?php
/**
 * Created by PhpStorm.
 * User: Duhyun K, Hailey S, Josh W, Sarah W
 * Date: 06/04/2020
 * Time: 12:30PM
 * Source to help get table formatted: https://www.youtube.com/watch?v=bHFoobciCTM;

 * Details: Checks naturalDisasterID from URl;
 * users are able to view a detailed report on specific
 * locations that were impacted by a natural disaster.
 * It will only show locations that have been filed with
 * claimants.
 */

require_once 'config.inc.php';
require_once 'headerList_NaturalDisaster.inc.php';

// Get disasterID from URL
$id = $_GET['id'];
if ($id === "") {
    header('location: list_naturalDisaster.php');
    exit();
}
if ($id === false) {
    header('location: list_naturalDisaster.php');
    exit();
}
if ($id === null) {
    header('location: list_naturalDisaster.php');
    exit();
}
?>
<html>
<head>
    <title>NaturalDisasters</title>
    <link rel="stylesheet" href="StyleSheets/base.css">
    <link rel="stylesheet" href="StyleSheets/tableSearchBarFormatting.css">
</head>
<body>
<div>
  <table class = table1>
      <h1>Details on a Natural Disaster</h1>
    <?php

    // Create connection
    $conn = new mysqli($servername, $username, $password, $database, $port);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT NaturalDisaster.disasterID, NaturalDisaster.disasterName, Impact.totalDeath,
    Impact.totalAffected, Impact.totalDamageCost, startDate, endDate, Location.isoCode,
    Location.stateCode, Location.cityName, Location.locationID, COUNT(*) AS 'ReportsFiled'
    FROM DisasterClaim
    INNER JOIN NaturalDisaster ON NaturalDisaster.disasterID = DisasterClaim.disasterID
    INNER JOIN Impact ON NaturalDisaster.disasterID = Impact.disasterID
    INNER JOIN Location ON Impact.locationID = Location.locationID
    WHERE (DisasterClaim.locationID = Location.locationID) AND (NaturalDisaster.disasterID = ?)
    GROUP BY Impact.locationID";

    $stmt = $conn->stmt_init();
    if (!$stmt->prepare($sql)) {
        echo "failed to prepare";
    }
    else {
        $stmt->bind_param('s',$id);
        $stmt->execute();
        $stmt->bind_result($disasterID, $disasterName, $totalDeath,
        $totalAffected, $totalDamageCost, $startDate, $endDate, $isoCode, $stateCode,
        $cityName, $locationID, $reportsFiled);

        echo "<div>";

        /* Used to only output the header row only once if a table can be created */
        $count = 1;
        $count1 = 0;
        while ($stmt->fetch()) {

          /* Displays the row header describing the columns only once */
          if ($count === 1) {
              $count1++;
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
          '</td><td>' . $disasterName. '</td><td>' . $totalDeath .
          '</td><td>' . $totalAffected. '</td><td>' . $totalDamageCost .
          '</td><td>' . $startDate . '</td><td>' . $endDate . '</td><td>' . $isoCode .'</td>' .
          '</td><td>' . $stateCode . '</td><td><a href="update_naturalDisaster.php?id=' . $disasterID .  '&locationID=' . $locationID . '">'
          . $cityName . '</td><td>' . $reportsFiled .'</td>';
          echo '</tr>';
          $count++;
        }
        echo "</div>";
    }
    if($count1 === 0)
    {
	?>
	No Detailed Data Avaliable.
	<?php
    }

    $conn->close();

    ?>
</table>
</div>
</body>
</html>
