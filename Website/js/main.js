/*
  Subjects variable, it holds
  all the subjects the FIB has
  up to the loading of the page
  as per the FIB API.
*/

var subjects;

/*
  Colors to be displayed by each
  subject in the schedule. All colors
  are materializecss colors.
*/

var takenColors = [{color:"teal",subject:null},
{color:"light-blue",subject:null},
{color:"red",subject:null},
{color:"green",subject:null},
{color:"lime",subject:null},
{color:"amber",subject:null},
{color:"orange",subject:null},
{color:"brown",subject:null}];

/*
  Slots variable. It holds all the slots in
  the schedule, in no particular order.
  The format of the slots are the same as the
  FIB API, for instance:
  {
          "codi_assig": "APA",
          "grup": "12",
          "dia_setmana": 2,
          "inici": "08:00",
          "durada": 2,
          "tipus": "L",
          "aules": "B5S201"
  }
*/

var slots = {slots:[]};

var solutionComputed;

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

function getRandomIndex() {
  var aux = [];
  for (var i = 0; i < takenColors.length; ++i)
    if (takenColors[i].subject == null)
      aux.push(i);
  var randomIndex = Math.round(Math.random()*(aux.length-1));
  return aux[randomIndex];
}

function getCellColor(subject) {
  var i = 0;
  while (i < takenColors.length && takenColors[i].subject != subject)
    ++i;
  if (i < takenColors.length)
    return takenColors[i].color;
  var idx = getRandomIndex();
  takenColors[idx].subject = subject;
  return takenColors[idx].color;
}

function putSlotInTable(slotToPut) {
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

function recordSlot(slot) {
  slots.slots.push(slot);
}

function processSubjectSlots(slotsObject) {
  for (var i = 0; i < slotsObject.slots.length; ++i) {
    var currentSlot = slotsObject.slots[i];
    recordSlot(currentSlot);
    var slotToPut = toStandardSlot(currentSlot);
    putSlotInTable(slotToPut);
  }
}

function addSubjectToSchedule(subject) {
  var selectedSemester = $("#selectSemester").find(":selected").text();
  var req = $.get("/cgi-bin/getSubjectInfo.py",{sem: selectedSemester,subj: subject});
  req.done(processSubjectSlots);
}

function deleteSubject(subject) {
  $("#scheduleTable").find("td:not(:first-child)")
  .find("div:contains("+subject+")").remove();
  for (var i = 0; i < takenColors.length; ++i) {
    if (takenColors[i].subject == subject) {
      takenColors[i].subject = null;
      break;
    }
  }
  var i = 0;
  while (i < slots.slots.length) {
    if (slots.slots[i].codi_assig == subject)
      slots.slots.splice(i,1);
    else
      ++i;
  }
}

function addSubject(subject) {
  if (solutionComputed == true) {
    solutionComputed = false;
    clearSchedule();
  }
  for (var i = 0; i < takenColors.length; ++i)
    if (takenColors[i].subject == subject)
      return;
  var $newSubject = $("<div> </div>").addClass("chip")
  .text("GRAU-" + subject);
  var $cross = $("<i> </i>").addClass("close material-icons")
  .text("close").click(function(){
    deleteSubject(subject);
  });
  $newSubject.append($cross);
  $("#selectedSubjects").append($newSubject);
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
      onAutocomplete: function(value) {
        var i = 0;
        while (value.charAt(i) != " ")
          ++i;
        $("#searchSubject").val("");
        addSubject(value.substring(0,i));
      }
    });
  });
}

function clearSchedule() {
  $("#scheduleTable").find("td:not(:first-child)").empty();
  $("#selectedSubjects").empty();
  for (var i = 0; i < takenColors.length; ++i) {
    takenColors[i].subject = null;
  }
  slots.slots = [];
}

function setUpSemesters() {
  setUpAutocomplete();
  $("#selectSemester").change(function() {
    solutionComputed = false;
    clearSchedule();
    setUpAutocomplete();
  });
}

function setSubjectList() {
  $.get("/cgi-bin/getSubjects.py",function(data) {
    subjects = data.subjects;
  }).done(setUpSemesters);
}

function warnEmptySlots() {
  Materialize.toast("No subjects in schedule.",1000);
}

function remoteSolutionCallback() {
  $.post("/cgi-bin/computeScheduleSolution.py",
    JSON.stringify(slots)
  ).done(displaySolvedSchedule);
}

function displayScheduleSolution(solutionObject) {
  for (var subject in solutionObject) {
    if (solutionObject.hasOwnProperty(subject)) {
      $("#scheduleTable td:not(:first-child) div:contains(" + 
         subject + "):not(:contains(" + solutionObject[subject][0] +
         ")):not(:contains(" + solutionObject[subject][1] + "))")
      .remove();      
    }
  }
}

function reflectSolution(solutionObject) {
  solutionComputed = true;
  var i = 0;
  while (i < slots.slots.length) {
    var currentSubject = slots.slots[i].codi_assig;
    var currentGroup = parseInt(slots.slots[i].grup);
    var solutionGroup = null;
    if (slots.slots[i].tipus == "L")
      solutionGroup = solutionObject[currentSubject][1];
    else
      solutionGroup = solutionObject[currentSubject][0];
    if (currentGroup != solutionGroup)
      slots.slots.splice(i,1);
    else
      ++i;
  }
}

function solutionNotFound() {
  clearSchedule();
  Materialize.toast("A solution couldn't be found",1000);
}

function displaySolvedSchedule(sol) {
  if (sol.hasOwnProperty("emptyResults")) {
    solutionNotFound();
    return;
  }
  reflectSolution(sol);
  displayScheduleSolution(sol);
  Materialize.toast("Solution found",1000);
}

function setUpComputeButton() {
  $("#computeButton").click(function(){
    if (slots.slots.length == 0)
      warnEmptySlots();
    else {
      remoteSolutionCallback();
    }
  });
}

function setUpEverything() {
  $("#selectSemester").material_select();
  setUpComputeButton();
  setSubjectList();
}

$(document).ready(function(){
  setUpEverything();
});























