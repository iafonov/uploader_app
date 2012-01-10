(function() {
  function files_list() {
    var file_item_template = _.template($("#file-item-template").text());
    var progress_bar = $("#progress_bar");
    var url = 'files.json';
    var files_table = $("#files_list");

    function render_list(data) {
      var list_html = _(data.files).reduce(function(memo, item) {
        return memo + file_item_template(item);
      }, "");

      progress_bar.hide();
      $("tr", files_table).not(".header").remove();
      files_table.append(list_html).show();
    }

    function download_data() {
      $.ajax({ url: url, success: render_list });
    }

    return {
      refresh: function() {
        progress_bar.show();
        download_data();
      }
    }
  }

  $(function() {
    var list = files_list();
    list.refresh();
  });
})();