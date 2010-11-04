// $Id:

Drupal.behaviors.js_logout = function (context) {
  var t = setTimeout(init, Drupal.settings.js_logout.timeout);
  
  function init() {
    if (Drupal.settings.js_logout.jquery_ui) {
      dialog();
    } else {
      if (confirm(Drupal.settings.js_logout.message) ) {
        refresh();    
      } else {
        logout();
      }
    }    
  }
  
  function dialog() {
    $('<div> ' +  Drupal.settings.js_logout.message + '</div>').dialog({
      modal: true,
      closeOnEscape: false,
      width: 'auto',
      buttons: { 
        Ok: function() {
          $(this).dialog("destroy");
          refresh();
        },
        Cancel: function() {
          $(this).dialog("destroy");
          logout();
        }
      },
      title: Drupal.settings.js_logout.title,
      close: function(event, ui) {
        logout();
      }
    });
  }

  function refresh() {
    $.ajax({
      url: Drupal.settings.basePath + 'js_logout_ahah_set_last',
      type: "POST",
      success: function() {
        t = setTimeout(init, Drupal.settings.js_logout.timeout);
      },
      error: function(XMLHttpRequest, textStatus) {
        alert('There has been an error resetting your last access time: ' + textStatus + '.')
      },
    });
  }
  
  function logout() {
    $.ajax({
      url: Drupal.settings.basePath + 'js_logout_ahah_logout',
      type: "POST",
      success: function() {
        document.location.href = Drupal.settings.js_logout.redirect_url;
      },
      error: function(XMLHttpRequest, textStatus) {
        alert('There has been an error attempting to logout: ' + textStatus + '.')
      },
    });
  }
};
