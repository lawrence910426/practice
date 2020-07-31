$(document).ready(function() {
    $('.submitted').hide();
    $("#submit").click(function() {
        $.ajax({
            url: "/robot",
            title: $("#title").val(),
            content: $("#content").val()
        }).always(function(resp) {
            var ans = resp.answer;
            $("#Answer_Content").css('background-color', ans)
            $("#Answer_Content_Text").text("This should be the '" + ans + "' party.")
            setTimeout(function() {
                $('.submitted').show();
                $('#Wait').modal('hide');
            }, 1000)
        })
    })
    $(".reply_send").click(function() {
        $.ajax({
            url: "/result",
            status: $(this).attr("code")
        }).always(function(resp) {
            
            setTimeout(function() {
                $('#Reply').modal('hide');
            }, 1000)
        })
    })
})