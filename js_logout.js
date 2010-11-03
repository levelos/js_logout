// $Id:

Drupal.behaviors.js_logout = function (context) {
  var t = setTimeout(logout, Drupal.settings.js_logout.timeout);
  
  function logout() {
    if (confirm(Drupal.settings.js_logout.message) ) {
      $.ajax({
        url: Drupal.settings.basePath + 'js_logout_ahah_set_last',
        type: "POST",
        success: function() {
          t = setTimeout(logout, Drupal.settings.js_logout.timeout);
        },
        error: function() {
          alert('There has been an error resetting your last access time.')
        },
      });      
    } else {
      $.ajax({
        url: Drupal.settings.basePath + 'js_logout_ahah_logout',
        type: "POST",
        success: function() {
          document.location.href = Drupal.settings.js_logout.redirect_url;
        },
        error: function() {
          alert('There has been an error attempting to logout.')
        },
      });
    }
  }
};
