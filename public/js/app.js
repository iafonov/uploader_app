function create_size_formatter() {
  var kb_template = _.template("{{kbytes}}K");
  var mb_template = _.template("{{mbytes}}M");

  return {
    format: function(size) {
      var converted_data = {
        kbytes: (size / 1024).toFixed(0),
        mbytes: (size / (1024 * 1024)).toFixed(2)
      };

      return converted_data.mbytes > 1 ?
        mb_template(converted_data) : kb_template(converted_data);
    }
  };
}

function create_list_controller() {
  var file_item_template = _.template($("#file-item-template").text());
  var progress_bar = $("#progress_bar");
  var url = 'files.json';
  var files_table = $("#files_list");
  var file_size_formatter = create_size_formatter();

  function render_list(data) {
    var list_html = _(data.files).reduce(function(memo, item) {
      item.size = file_size_formatter.format(item.size);
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
  var on_upload_start_handler = function() {};
  var on_upload_complete_handler = function() {};

  function generate_uid() {
    return _("abcdefghijklmnopqrstuvwxyz".split("")).shuffle().join('');
  }

  function reset_form() {
    var upload_uid = generate_uid();
    var url = _.template("/files/new/{{upload_uid}}", { upload_uid: upload_uid });

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
  }

  reset_form();

  return {
    add_upload_start_handler: function(cb) {
      on_upload_start_handler = _.compose(on_upload_start_handler, cb);
    },
    add_upload_complete_handler: function(cb) {
      on_upload_complete_handler = _.compose(on_upload_complete_handler, cb);
      reset_form();
    }
  };
}

function create_upload_progress_controller() {
  var progress_info = $("#upload_progress");
  var timer_id, uid;
  var url_template = _.template("/files/status/{{upload_uid}}");
  var file_size_formatter = create_size_formatter();
  var uploaded_prev;

  function format_progress(uploaded, size) {
    var stats = {
      percents: ((uploaded / size) * 100).toFixed(0),
      uploaded_kb: file_size_formatter.format(uploaded),
      size_kb: file_size_formatter.format(size),
      speed_kb: file_size_formatter.format(uploaded - uploaded_prev)
    };

    uploaded_prev = uploaded;
    return _.template("{{percents}}% ({{uploaded_kb}} of {{size_kb}}, {{speed_kb}}/sec)", stats);
  }

  function render_progress(data) {
    progress_info.html(format_progress(data.uploaded, data.size));
  }

  function update_progress() {
    $.get(url_template({upload_uid: uid})).success(render_progress);
  }

  return {
    start: function(upload_uid) {
      uploaded_prev = 0;
      progress_info.show();
      uid = upload_uid;
      timer_id = window.setInterval(update_progress, 1000);
    },
    stop: function() {
      progress_info.html("Upload complete").delay(1000).fadeOut();
      window.clearInterval(timer_id);
    }
  };
}

function app() {
  var list_controller = create_list_controller();
  var upload_controller = create_upload_controller();
  var upload_progress_controller = create_upload_progress_controller();

  upload_controller.add_upload_start_handler(upload_progress_controller.start);
  upload_controller.add_upload_complete_handler(upload_progress_controller.stop);
  upload_controller.add_upload_complete_handler(list_controller.refresh);

  return {
    init: function() {
      list_controller.refresh();
    }
  };
}

$(function() {
  app().init();
});