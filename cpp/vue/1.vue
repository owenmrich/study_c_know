
    <div id="test">
       <label for="agree">
        <inout type="checkbox" value="足球" v-model="hobbies">足球
        </label>
        <label for="agree">
            <inout type="checkbox" value="篮球" v-model="hobbies">篮球
        </label>
        <label for="agree">
            <inout type="checkbox" value="羽毛球" v-model="hobbies">羽毛球
        </label>
        <h2>您的爱好是: {{hobbies}}</h2>
    </div>
    const app = new Vue({
        el:'#test'
        data:{
            isAgree: false,
            hobbies: []
            conet:"<a herf="url">11</a>"
            arr:["1","2","2"]
        }
    })

<div>
    <h2 v-test = "msg"></h2>
    <h2 v-html = "url"></h2>
    <p v-if = "isAgree (false/ture)"></p>
    <img src="addr" v-show="isAgree (false/ture)"></img>
    <img :src="" class="{active:isAgree}"></img>
    <li v-for="item in arr">{{item}}</li>
    <input type="button" v-on:click="method"></input>
</div>