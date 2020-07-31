$(document).ready(function() {
    $('.submitted').hide();
    $("#submit").click(function() {
        setTimeout(function() {
            $('.submitted').show();
            $('#Wait').modal('hide');
        }, 3000)
    })
    
})