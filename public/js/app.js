function create_list_controller() {
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
    $.get('files.json').success(render_list);
  }

  return {
    refresh: function() {
      progress_bar.show();
      download_data();
    }
  };
}

function create_upload_controller() {
  var on_upload_complete_handlers = [];

  $('#file_input').fileupload({
    dataType: 'json',
    url: '/files/new',
    progress: function(e, data) {
      console.log("progress");
    },
    done: function(e, data) {
      console.log("done");
      _(on_upload_complete_handlers).each(function(cb) { cb(); });
    }
  });

  return {
    add_upload_complete_handler: function(cb) {
      on_upload_complete_handlers.push(cb);
    }
  }
}

function create_comment_controller() {
  var ready_to_submit = false;
  var submit_button = $("#upload_submit");
  var comment_input = $("#file_description");

  function submit() {
    console.log("SUBMIT:" + comment_input.val());
  }

  function switch_to_saved_mode() {
    submit_button.attr("disabled", "disabled").val("Saved");
    $(".active-comment").hide();
    $(".passive-comment").show();
    $("#file_description_text").text(comment_input.val());
  }

  return {
    on_save: function() {
      switch_to_saved_mode();
      return false;
    },
    set_ready_for_submit: function() {
      ready_to_submit = true;
    }
  };
}

function app() {
  var list_controller = create_list_controller();
  var upload_controller = create_upload_controller();
  var comment_controller = create_comment_controller();

  upload_controller.add_upload_complete_handler(list_controller.refresh);
  upload_controller.add_upload_complete_handler(comment_controller.set_ready_for_submit);

  return {
    init: function() {
      $("#file_upload").submit(comment_controller.on_save);
      list_controller.refresh();
    }
  };
}

$(function() {
  app().init();
})