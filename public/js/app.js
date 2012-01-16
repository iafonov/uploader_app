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
      console.log("refresh");
      progress_bar.show();
      download_data();
    }
  };
}

function create_upload_controller() {
  var on_upload_start_handler = function() {};
  var on_upload_complete_handler = function() {};
  var upload_uid = generate_uid();

  var url = _.template("/files/new/{{upload_uid}}", { upload_uid: upload_uid });

  function generate_uid() {
    return _("abcdefghijklmnopqrstuvwxyz".split("")).shuffle().join('');
  }

  $('#file_input').fileupload({
    dataType: 'json',
    url: url,
    start: function(e, data) {
      on_upload_start_handler(upload_uid);
    },
    stop: function(e, data) {
      on_upload_complete_handler(upload_uid);
    }
  });

  return {
    add_upload_start_handler: function(cb) {
      on_upload_start_handler = _.compose(on_upload_start_handler, cb);
    },
    add_upload_complete_handler: function(cb) {
      on_upload_complete_handler = _.compose(on_upload_complete_handler, cb);
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
      console.log("set_ready_for_submit");
      ready_to_submit = true;
    }
  };
}

function create_upload_progress_controller() {
  var progress_info = $("#upload_progress");
  var timer_id, uid;
  var url_template = _.template("/files/status/{{upload_uid}}");

  function render_progress(data) {
    progress_info.html(data.uploaded);
  }

  function update_progress() {
    $.get(url_template({upload_uid: uid})).success(render_progress);
  }

  return {
    start: function(upload_uid) {
      uid = upload_uid;
      timer_id = window.setInterval(update_progress, 1000);
    },
    stop: function() {
      window.clearInterval(timer_id);
      console.log("upload_progress_controller:stop");
    }
  }
}

function app() {
  var list_controller = create_list_controller();
  var upload_controller = create_upload_controller();
  var comment_controller = create_comment_controller();
  var upload_progress_controller = create_upload_progress_controller();

  upload_controller.add_upload_start_handler(upload_progress_controller.start);
  upload_controller.add_upload_complete_handler(upload_progress_controller.stop);
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