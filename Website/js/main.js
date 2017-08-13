var input = $("#subjects .typeahead");
input.typeahead({
  source: [
    {id: "test1", name: "Test 1"},
    {id: "test2", name: "Test 2"},
  ],
  autoSelect: true,
  hint: true
});