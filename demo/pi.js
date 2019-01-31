//
// 计算 PI, 这是个耗时操作, 用于测试多线程
// PlayJS: 1000000000 耗时 13.598 seconds
// Nodejs: 1000000000 耗时 13.089 seconds
//
calculate(200000000);


function calculate(num) {
    //var num = document.myForm.num.value;
    var pi = 4, top = 4, bot = 3, minus = true;
    next(pi, top, bot, minus, num);
}


function next(pi, top, bot, minus, num) {
    var cur_time = Date.now();
    var sh = num / 10;

    for (var i = 0; i < num; i++) {
        pi += (minus == true) ? -(top / bot) : (top / bot);
        minus = !minus;
        bot += 2;
        if (i % sh == 0) {
            console.log("Count", i, "PI", pi);
        }
    }

    var end_time = Date.now();
    var total_time = end_time - cur_time;

    if (total_time >= 1000) {
        total_time = (total_time / 1000) + " seconds";
    } else {
        total_time += " ms";
    }

    console.log("Count", num, "PI", pi);
    console.log("Result calculated in: " + total_time + "...");
}


