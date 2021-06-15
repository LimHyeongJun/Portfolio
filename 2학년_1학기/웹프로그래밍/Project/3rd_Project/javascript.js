
/*목록 배경색 지정*/
$(document).ready(function() {
    $('.table_td_menu > td:odd').css('background', 'rgb(248, 225, 243)');
    $('.table_td_menu > td:even').css('background', 'rgb(249, 252, 217)');
});

/*이미지에 마우스 올리면 크기 1.5배 됐다가 벗어나면 원래 크기로*/
$(document).ready(function() {
    $("img").on({
        mouseenter: function() {$(this).addClass('scale_animate');},
        mouseleave: function() {$(this).removeClass('scale_animate');}
    });
});

/*목록 메뉴에 마우스 올리면 그라데이션 효과 주기*/
$(document).ready(function() {
    $('.table_td_menu > td:odd').mouseenter(function() {
        $(this).css('background-image', 'linear-gradient(to right, rgb(248, 225, 243), white)');
    });
    $('.table_td_menu > td:odd').mouseleave(function() {
        $(this).css('background', 'rgb(248, 225, 243)');
    });
    $('.table_td_menu > td:even').mouseenter(function() {
        $(this).css('background-image', 'linear-gradient(to right, rgb(249, 252, 217), white)');
    });
    $('.table_td_menu > td:even').mouseleave(function() {
        $(this).css('background', 'rgb(249, 252, 217)');
    });
});

/*KBOteam.html에서 현재 프로야구 구단 10개 설명 테이블에 그라데이션 효과*/
$(document).ready(function() {
    $('.table_td_baseball_team:nth-child(12n+2)').css('background', 'white'); /*rgb(128, 128, 128)*/
    $('.table_td_baseball_team:nth-child(12n+3)').css('background', 'rgb(240, 240, 240)'); 
    $('.table_td_baseball_team:nth-child(12n+4)').css('background', 'rgb(226, 226, 226)');
    $('.table_td_baseball_team:nth-child(12n+5)').css('background', 'rgb(212, 212, 212)');
    $('.table_td_baseball_team:nth-child(12n+6)').css('background', 'rgb(198, 198, 198)');
    $('.table_td_baseball_team:nth-child(12n+7)').css('background', 'rgb(184, 184, 184)');
    $('.table_td_baseball_team:nth-child(12n+8)').css('background', 'rgb(170, 170, 170)');
    $('.table_td_baseball_team:nth-child(12n+9)').css('background', 'rgb(156, 156, 156)');
    $('.table_td_baseball_team:nth-child(12n+10)').css('background', 'rgb(142, 142, 142)');
    $('.table_td_baseball_team:nth-child(12n+11)').css('background', 'gray'); /*rgb(255, 255, 255)*/
});

/*survey.html에서 마지막 자유의견 쓰는거에서 몇 글자 더 쓸수 있는지, 특정 글자부터 색깔 바뀌는지*/
$(document).ready(function() {
    $('textarea').focus(function() {
        $(this).css("background-color", "rgb(198, 198, 198)");
    });
    $('textarea').blur(function() {
        $(this).css("background-color", "white");
    });
    $('textarea').keyup(function() {
        var inputLength = $(this).val().length;
        if(inputLength > 300) inputLength = 300;
        var remain = 300 - inputLength;

        $('h2').html(remain);

        if(remain >= 30) $('h2').css('color', 'blank');
        else if(remain > 0) $('h2').css('color', 'rgb(158, 175, 4)');
        else if(remain == 0) $('h2').css('color', 'red');
    });
});

/*설문조사 제출 버튼 누르면 뜨는 팝업창*/
$(document).ready(function() {
    $('.submit_result').click(function() {
        alert('설문조사에 참여해주셔서 감사드립니다!');
    });
});

/*설명란 마우스 이벤트*/
$(document).ready(function() {
    $("#explanation_background").on({
        mouseenter: function() {
            $(this).css("background-image", "linear-gradient(to right, rgb(118, 245, 79), yellow,rgb(118, 245, 79)");
        },
        mouseleave: function() {
            $(this).css("background-image", "linear-gradient(to right, rgb(99, 149, 241), white,rgb(99, 149, 241)");
        }
    });
});