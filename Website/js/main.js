var subjects;
var takenColors = [{color:"teal",picked:false},
{color:"light-blue",picked:"false"},
{color:"red",picked:false},
{color:"green",picked:false},
{color:"lime",picked:false},
{color:"amber",picked:false},
{color:"orange",picked:false},
{color:"brown",picked:false}];


function getRowFromSlot(slotString) {
  return parseInt(slotString.substr(0,2)) - 7;
}

function toStandardSlot(slotObject) {
  var row = getRowFromSlot(slotObject.inici);
  return {name: slotObject.codi_assig,
  group: slotObject.grup,type: slotObject.tipus,
  row: row,column: slotObject.dia_setmana,
  duration: slotObject.durada}
}

function getCellColor(subject) {
  var i = 0;
  while (i < takenColors.length && takenColors[i].picked == false &&
  takenColors[i].subj != subject)
    ++i;
  if (i < takenColors.length)
    return takenColors[i].color;
  var index = Math.random()*(takenColors.length-1);
  index = Math.round(index);
  while (takenColors[index].picked == false) {
    index = Math.round(Math.random()*(takenColors.length-1));
  }
  takenColors[index].picked = true;
  takenColors[index].subj = subject;
  return takenColors[index].color;
}

function putSlot(slotToPut) {
  var table = $("#scheduleTable").get(0);
  for (var i = slotToPut.row; i <= slotToPut.row + slotToPut.duration - 1;++i) {
    var cell = table.rows[i].cells[slotToPut.column];
    var $cell = $(cell);
    var cellString = slotToPut.name + " " + slotToPut.group +
    " " + slotToPut.type;
    var color = getCellColor(slotToPut.name);
    var $cellContent = $("<div> </div>").addClass(color);
    if ($cell.children().length > 0) {
      $cellContent.attr("style","margin-top: 10px;");
    }
    $cellContent.text(cellString);
    $cell.append($cellContent);
  }
}

function processSubjectSlots(slotsObject) {
  for (var i = 0; i < slotsObject.slots.length; ++i) {
    var currentSlot = slotsObject.slots[i];
    var slotToPut = toStandardSlot(currentSlot);
    putSlot(slotToPut);
  }
}

function addSubjectToSchedule(subject) {
  var selectedSemester = $("#selectSemester").find(":selected").text();
  var req = $.get("/cgi-bin/getSubjectInfo.py",{sem: selectedSemester,subj: subject});
  req.done(processSubjectSlots);
}

function addSubject(subject) {
  var oldHtml = $("#selectedSubjects").html();
  $("#selectedSubjects").html(
    oldHtml + '<div class="chip"> GRAU-' + subject +
    '<i class="close material-icons" >close</i>' + '</div>'
  );
  addSubjectToSchedule(subject);
}

function setUpAutocomplete() {
  var selectedSemester = $("#selectSemester").find(":selected").text();
  var aux = {};
  $.get("/cgi-bin/getSemesterSubjects.py",{sem: selectedSemester}, function(data) {
    for (var i = 0; i < data.subjects.length; ++i) {
      var j = 0;
      while (j < subjects.length && subjects[j].id != data.subjects[i])
        ++j;
      if (j < subjects.length) {
        aux[data.subjects[i] + " - " + subjects[j].name] = null
      }
    }
  }).done(function(){
    $("#searchSubject").autocomplete({
      data: aux,
      limit: 5,
      onAutocomplete: function(val) {
        var i = 0;
        while (val.charAt(i) != " ")
          ++i;
        addSubject(val.substring(0,i));
      }
    });
  });
}

function setUpSemesters() {
  setUpAutocomplete();
  $("#selectSemester").change(function() {
    setUpAutocomplete();
  });
}

function setSubjectList() {
  $.get("/cgi-bin/getSubjects.py",function(data) {
    subjects = data.subjects;
  }).done(setUpSemesters);
}

function setUpEverything() {
  $("#selectSemester").material_select();
  setSubjectList();
}

$(document).ready(function(){
  setUpEverything();
});























