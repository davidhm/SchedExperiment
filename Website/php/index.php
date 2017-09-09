<!DOCTYPE html>
<html lang="es">
<head>
  <title>Test</title>
  <meta charset="utf-8">
  <meta name="viewpoert" content="width=device-width, initial-scale=1">
  <!--Import Google Icon Font-->
  <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
  <!--Import materialize.css-->
  <link type="text/css" rel="stylesheet" href="../css/materialize.min.css"  media="screen,projection"/>
  <!--Jquery-->
  <script src="../js/jquery-3.2.1.js"></script>
  <!--Materialize javascript-->
  <script src="../js/materialize.min.js"></script>
  <script src="../js/main.js"></script>
</head>
<body>
  <div class="container">
    <div class="row" style="margin-top: 50px;">
      <div class="input-field col l3">
        <select id = "selectSemester">
          <?php
            $ch = curl_init("https://api.fib.upc.edu/v2/quadrimestres/");
            $headers = array("Accept: application/json",
            "client_id: Hqyble56qaamSD2jzZcbO9BlYEM8zWPlQdNqFk4H");
            curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
            curl_setopt($ch,CURLOPT_HTTPHEADER,$headers);
            $res = curl_exec($ch);
            $object = json_decode($res);
            $counter = 1;
            foreach ($object->results as $semester) {
              if ($semester->actual == "S")
                echo "<option value = \"$counter\" selected>$semester->id</option>\n";
              else
                echo "<option value = \"$counter\">$semester->id</option>\n";
              ++$counter;
            }
          ?>
        </select>
      </div>
      <div class="offset-l9">
      </div>
    </div>
    <div class="row">
      <div class="col l5 s12">
        <div class="input-field">
          <input type="text" id="searchSubject" class="autocomplete" autocomplete="off">
          <label for="searchSubject">Search subject...</label>
        </div>
        <div id="selectedSubjects">
        </div>
        <div id = "computeButton" class="btn">
          Compute!
        </div>
      </div>
      <div class="col l7 s12">
        <table id = "scheduleTable" class="bordered centered">
          <thead>
            <tr>
              <th></th>
              <th>Monday</th>
              <th>Tuesday</th>
              <th>Wednesday</th>
              <th>Thursday</th>
              <th>Friday</th>
            </tr>
          </thead>
          <tbody>
            <?php
              for ($i = 8; $i <= 20; ++$i) {
                echo "<tr>";
                echo "<td>";
                echo "$i-",$i+1,"h";
                echo "</td>";
                for ($j = 1; $j <= 5; ++$j) {
                  echo "<td></td>";
                }
              }
            ?>
          </tbody>
        </table>
      </div>
    </div>
  </div>
</body>
</html>