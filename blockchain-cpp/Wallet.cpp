#include "Wallet.h"

Wallet::Wallet() {
    generateKeyPair();
}

EC_GROUP* Wallet::getDefaultEcGroup() {
    EC_GROUP* ecGroup = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1);
    EC_GROUP_set_asn1_flag(ecGroup, OPENSSL_EC_NAMED_CURVE);
    point_conversion_form_t form = POINT_CONVERSION_UNCOMPRESSED;
    EC_GROUP_set_point_conversion_form(ecGroup, form);

    return ecGroup;
}

int Wallet::generateKeyPair() {
    EVP_PKEY_CTX* ctx;

    int ret = 1;
    BIO* bio_private = BIO_new_file("private_new.pem", "w+");
    BIO* bio_public = BIO_new_file("public_new.pem", "w+");
    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL);
    if (ctx == NULL)
        goto err;
    if (EVP_PKEY_keygen_init(ctx) <= 0)
        goto err;
    if (EVP_PKEY_CTX_set_ec_paramgen_curve_nid(ctx, NID_X9_62_prime256v1) <= 0)
        goto err;

    if (EVP_PKEY_keygen(ctx, &pkey) <= 0)
        goto err;
    StringUtil::printfGreen("\nGenerate Wallet successfully!\n");

    ret = PEM_write_bio_PrivateKey(bio_private, pkey, NULL, NULL, 0, NULL, NULL);
    BIO_flush(bio_private);

    ret = PEM_write_bio_PUBKEY(bio_public, pkey);
    BIO_flush(bio_public);
    ret = 0;
    publicKeyChar = StringUtil::publicKeyToUnsignedChar(pkey);
    StringUtil::printfGreen("PublicKey:");
    cout << publicKeyChar << endl;
    privateKeyChar = StringUtil::privateKeyToUnsignedChar(pkey);
    StringUtil::printfGreen("PrivateKey:");
    cout << privateKeyChar << endl;
err:
    EVP_PKEY_CTX_free(ctx);
    return ret;
}
