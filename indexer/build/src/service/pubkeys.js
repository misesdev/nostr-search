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
exports.listPubkeys = void 0;
const disk_1 = require("../filesytem/disk");
const utils_1 = require("../utils");
const listPubkeys = (pool, author, userCount) => __awaiter(void 0, void 0, void 0, function* () {
    const events = yield pool.fechEvents({
        authors: [author],
        kinds: [3],
        limit: 1
    });
    if (events.length) {
        const pubkeys = (0, utils_1.getPubkeys)(events[0]);
        let skipe = pubkeys.length, nofound = 0;
        for (let i = 0; nofound < 10; i += skipe) {
            let authors = pubkeys.slice(i, i + skipe);
            let events = yield pool.fechEvents({
                authors: authors,
                kinds: [3],
                limit: skipe
            });
            if (!events.length)
                nofound++;
            events.forEach(event => {
                let npubs = (0, utils_1.getPubkeys)(event);
                console.log("npubs", npubs.length);
                npubs.forEach(pubkey => {
                    if (!pubkeys.includes(pubkey))
                        pubkeys.push(pubkey);
                });
            });
        }
        const file = new disk_1.FileSystem("pubkeys.db");
        pubkeys.forEach(pubkey => file.writeLine(pubkey));
        console.log("users:", pubkeys.length);
    }
});
exports.listPubkeys = listPubkeys;
