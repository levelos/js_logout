// $Id:

Drupal.behaviors.js_logout = function (context) {
  var t = setTimeout(logout, Drupal.settings.js_logout.timeout);
  
  function logout() {
    if (confirm(Drupal.settings.js_logout.message) ) {
      t = setTimeout(logout, Drupal.settings.js_logout.timeout);
    } else {
      $.ajax({
        url: Drupal.settings.basePath + 'js_logout',
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
