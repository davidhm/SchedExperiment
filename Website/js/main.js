function addSubject(subject) {
  var oldHtml = $("#selectedSubjects").html();
  $("#selectedSubjects").html(
    oldHtml + '<div class="chip">' + subject +
    '<i class="close material-icons">close</i>'+
    '</div>'
  );
}

$(document).ready(function(){
  $("input.autocomplete").autocomplete({
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
  $("select").material_select();
});
