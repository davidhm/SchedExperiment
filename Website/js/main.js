var subjects;

function addSubject(subject) {
  var oldHtml = $("#selectedSubjects").html();
  $("#selectedSubjects").html(
    oldHtml + '<div class="chip">' + subject +
    '<i class="close material-icons" >close</i>' + '</div>'
  );
}

function setUpAutocomplete() {
  var selectedSemester = $("#selectSemester").find(":selected").text();
  var aux = {};
  $.get("/cgi-bin/getSemesterSubjects.py",{sem: selectedSemester}, function(data) {
  });
  $("#searchSubject").autocomplete({
    data: aux,
    limit: 10,
    onAutocomplete: function(val) {
      var i = 0;
      while (val.charAt(i) != "-")
        ++i;
      addSubject("GRAU-" + val.substr(0,i-1));
    }
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
  });
}

function setUpEverything() {
  setSubjectList();
  setUpSemesters();
}

$(document).ready(function(){
  setUpEverything();
});























