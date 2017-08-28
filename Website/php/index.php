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
        <div class="btn">
          Compute!
        </div>
      </div>
      <div class="col l7 s12">
        <table class="bordered centered">
          <thead>
            <tr>
              <th>Monday</th>
              <th>Tuesday</th>
              <th>Wednesday</th>
              <th>Thursday</th>
              <th>Friday</th>
            </tr>
          </thead>
          <tbody id ="scheduleContent">
            <tr>
              <td>08:00</td>
            </tr>
            <tr>
              <td>09:00</td>
            </tr>
            <tr>
              <td>10:00</td>
            </tr>
            <tr>
              <td>11:00</td>
            </tr>
            <tr>
              <td>12:00</td>
            </tr>
            <tr>
              <td>13:00</td>
            </tr>
            <tr>
              <td>14:00</td>
            </tr>
            <tr>
              <td>15:00</td>
            </tr>
            <tr>
              <td>16:00</td>
            </tr>
            <tr>
              <td>17:00</td>
            </tr>
            <tr>
              <td>18:00</td>
            </tr>
            <tr>
              <td>19:00</td>
            </tr>
            <tr>
              <td>20:00</td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
  </div>
</body>
</html>