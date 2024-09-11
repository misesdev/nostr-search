"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
const up_1 = require("./src/service/up");
const author = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27";
const main = () => __awaiter(void 0, void 0, void 0, function* () {
    //const relayPool = new RelayPool(relays)
    //await relayPool.connect();
    //await listPubkeys(relayPool, author, 5000) 
    //await listUsers(relayPool)
    (0, up_1.loadData)();
});
main();
