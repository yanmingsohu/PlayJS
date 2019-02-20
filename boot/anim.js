export default {
  FixedWalk,
};

//
// 固定行走动画
// TODO: 参数都与模型和骨骼绑定, 不通用.
//
function FixedWalk(animData) {
  let rand = Math.random();
  // ske 的定义可能改变
  let rightFoot = animData.getOffset(0);
  let leftFoot  = animData.getOffset(1);
  let rightHead = animData.getOffset(3);
  let leftHead  = animData.getOffset(4);
  let mawe1     = animData.getOffset(5);
  let eye       = animData.getOffset(6);

  const thiz = {
    draw,
  };
  return thiz;

  //
  // 下一帧动画
  //
  function draw(used, time) {
    // matrix.vec4.rotateX(rightFoot, rightFoot, used);
    time += rand;
    let speed = 8;
    let pos = time*speed;
    let ssin = Math.sin(pos);
    let scos = Math.cos(pos);

    rightFoot[1] = ssin/8;
    rightFoot[2] = -scos/50;

    leftFoot[1] = -ssin/8;
    leftFoot[2] = scos/50;

    rightHead[1] = -ssin/20;
    leftHead[1]  = ssin/20;

    pos = time*(speed-2)
    // mawe1[1] = Math.sin(pos)/50;
    mawe1[2] = scos/70;
    eye[2] = (parseInt(time*10)%40 < 2)? -0.09: 0;
  }
}