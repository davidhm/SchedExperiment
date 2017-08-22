function addSubject(subject) {
  var oldHtml = $("#selectedSubjects").html();
  $("#selectedSubjects").html(
    oldHtml + '<div class="chip">' + subject +
    '<i class="close material-icons" >close</i>' + '</div>'
  );
}

function changeTabToEnter() {
  $("#searchSubject").on("keydown",function(key){
    if (key.which = 9) {
      var e = jQuery.Event("keydown");
      e.which = 13;
      $("input").trigger(e);
    }
  })
}

function setUpMaterialize() {
  $("#searchSubject").autocomplete({
    data: {
      "Apple": null,
      "Microsoft": null,
      "Google": null
    },
    limit: 20, // The max amount of results that can be shown at once. Default: Infinity.
    onAutocomplete: function(val) {
      addSubject(val);
    },
    minLength: 1, // The minimum length of the input for the autocomplete to start. Default: 1.
  });
}

function setUpSemesters() {
  $.get("/cgi-bin/getSemesters.py",function(data) {
    var aux = $("#selectSemester");
    aux.html(data);
    aux.material_select();
  });
}

function setUpEverything() {
  setUpMaterialize();
  setUpSemesters();
}

$(document).ready(function(){
  setUpEverything();
});























